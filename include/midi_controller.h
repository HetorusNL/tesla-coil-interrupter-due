#ifndef MidiController_h
#define MidiController_h

#include "packet_handler_constants.h"
#include "timer_manager.h"

class MidiController {
 public:
  MidiController();
  ~MidiController();

  // packet handler functions
  PHC::PACKET_HANDLE_RESULT startStream(uint8_t* data, uint8_t len);
  PHC::PACKET_HANDLE_RESULT handleMessage(uint8_t* data, uint8_t len);
  PHC::PACKET_HANDLE_RESULT endStream(uint8_t* data, uint8_t len);
  PHC::PACKET_HANDLE_RESULT performReset();

  // processes a 3-char midi message
  bool processMessage(uint8_t* msg);

 private:
  void noteOn(uint8_t* msg);
  void noteOff(uint8_t* msg);
  void stopAllNotes();

 private:
  TimerManager timerManager;
  struct MidiTone {
    bool used;
    uint8_t channel;
    uint8_t note;
    uint8_t velocity;
    uint16_t delay;
    CoilTimer* coilTimer;
  };
  MidiTone midiTones[TimerManager::NUM_TIMERS];

  // precomputed MIDI frequencies
  // calculation, where rootNote = 440Hz, note = MIDI note:
  // rootNote * pow(2., ((double)note - 69) / 12)
  static constexpr float midiFrequency[] = {
      8.175798916, 8.661957218, 9.177023997, 9.722718241, 10.30086115,
      10.91338223, 11.56232571, 12.24985737, 12.9782718,  13.75,
      14.56761755, 15.43385316, 16.35159783, 17.32391444, 18.35404799,
      19.44543648, 20.60172231, 21.82676446, 23.12465142, 24.49971475,
      25.9565436,  27.5,        29.13523509, 30.86770633, 32.70319566,
      34.64782887, 36.70809599, 38.89087297, 41.20344461, 43.65352893,
      46.24930284, 48.9994295,  51.9130872,  55,          58.27047019,
      61.73541266, 65.40639133, 69.29565774, 73.41619198, 77.78174593,
      82.40688923, 87.30705786, 92.49860568, 97.998859,   103.8261744,
      110,         116.5409404, 123.4708253, 130.8127827, 138.5913155,
      146.832384,  155.5634919, 164.8137785, 174.6141157, 184.9972114,
      195.997718,  207.6523488, 220,         233.0818808, 246.9416506,
      261.6255653, 277.182631,  293.6647679, 311.1269837, 329.6275569,
      349.2282314, 369.9944227, 391.995436,  415.3046976, 440,
      466.1637615, 493.8833013, 523.2511306, 554.365262,  587.3295358,
      622.2539674, 659.2551138, 698.4564629, 739.9888454, 783.990872,
      830.6093952, 880,         932.327523,  987.7666025, 1046.502261,
      1108.730524, 1174.659072, 1244.507935, 1318.510228, 1396.912926,
      1479.977691, 1567.981744, 1661.21879,  1760,        1864.655046,
      1975.533205, 2093.004522, 2217.461048, 2349.318143, 2489.01587,
      2637.020455, 2793.825851, 2959.955382, 3135.963488, 3322.437581,
      3520,        3729.310092, 3951.06641,  4186.009045, 4434.922096,
      4698.636287, 4978.03174,  5274.040911, 5587.651703, 5919.910763,
      6271.926976, 6644.875161, 7040,        7458.620184, 7902.13282,
      8372.01809,  8869.844191, 9397.272573, 9956.063479, 10548.08182,
      11175.30341, 11839.82153, 12543.85395};
};

#endif  // MidiController_h