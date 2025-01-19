#include "RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#define SAMPLE_RATE 44100
#define SAMPLE_TYPE RTAUDIO_FLOAT64
#define FRAMES_PER_BUFFER 512
 
// Pass-through function.
int inout( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
           double streamTime, RtAudioStreamStatus status, void *data )
{
  // Since the number of input and output channels is equal, we can do
  // a simple buffer copy operation here.
  if ( status ) std::cout << "Stream over/underflow detected." << std::endl;

  unsigned int *bytes = (unsigned int *) data;
  memcpy( outputBuffer, inputBuffer, *bytes );
  return 0;
}
 
int main()
{
  RtAudio adac;
  std::vector<unsigned int> deviceIds = adac.getDeviceIds();
  if ( deviceIds.size() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }


  RtAudio::DeviceInfo info;
  for ( unsigned int n=0; n<deviceIds.size(); n++ ) {
    info = adac.getDeviceInfo( deviceIds[n] );
    std::cout << "device name = " << info.name << std::endl;
    std::cout << ": max input channels = " << info.inputChannels << std::endl;
    std::cout << ": max output channels = " << info.outputChannels << std::endl;
  }

 
  unsigned int bufferBytes, bufferFrames = FRAMES_PER_BUFFER;
  RtAudio::StreamParameters iParams, oParams;

  int i = 0;
  RtAudio::DeviceInfo inputInfo;
  do {
    inputInfo = adac.getDeviceInfo( deviceIds[i] );
    iParams.deviceId = deviceIds[i];
    iParams.nChannels = inputInfo.inputChannels;
    i++;
  } while (inputInfo.inputChannels == 0);

  int j = 0;
  RtAudio::DeviceInfo outputInfo;
  do {
    outputInfo = adac.getDeviceInfo( deviceIds[j] );
    oParams.deviceId = deviceIds[j];
    oParams.nChannels = outputInfo.outputChannels;
    j++;
  } while (outputInfo.outputChannels == 0);

  std::cout<< "input device  = " << inputInfo.name << std::endl;
  std::cout<< "output device = " << outputInfo.name << std::endl;
 
  if ( adac.openStream( &oParams, &iParams, SAMPLE_TYPE, SAMPLE_RATE,
                        &bufferFrames, &inout, (void *)&bufferBytes ) ) {
    std::cout << '\n' << adac.getErrorText() << '\n' << std::endl;
    exit( 0 ); // problem with device settings
  }
 
  bufferBytes = bufferFrames * (outputInfo.outputChannels / inputInfo.inputChannels) * sizeof( float );
 
  if ( adac.startStream() ) {
    std::cout << adac.getErrorText() << std::endl;
    goto cleanup;
  }
 
  char input;
  std::cout << "\nRunning ... press <enter> to quit.\n";
  std::cin.get(input);
 
  // Block released ... stop the stream
  if ( adac.isStreamRunning() )
    adac.stopStream();  // or could call adac.abortStream();
 
 cleanup:
  if ( adac.isStreamOpen() ) adac.closeStream();
 
  return 0;
}