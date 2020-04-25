#include "gmock/gmock.h"  // Brings in Google Mock.

#include "event.hpp"
#include "memory.hpp"
#include "avr_timer.hpp"


using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class Monitor 
{
	public:
	Monitor()
	{
		current_state = false;
		sample_count = 0;
	}
	
	
	
	void Sample()
	{
		if (current_state == false)
		{
			sample_count++;
			if (sample_count >= 10)
			{
				current_state = true;
			}
		}
		else if (current_state == true)
		{
			sample_count++;
			if (sample_count >= 10)
			{
				current_state = false;
			}
		}
		else
		{
			sample_count = 0;
		}
	}

    bool getCurrentState()
    {
        return current_state;
    }
	
	private:
	bool current_state;
	uint8_t sample_count;
};


Monitor monitor;

void TestHandler()
{
	monitor.Sample();
}

TEST(DebugConsoleTest, buffer_elements_and_pushed_data_should_be_same)
{
	Shrine::InitializeTimer();
	Shrine::System & system = Shrine::System::Instance();


	
	Shrine::Timer timer;
	timer.Callback(TestHandler);
	timer.Type(Shrine::TimerType::REPETATIVE);
	timer.Period(Shrine::TickType(10));
	timer.Start();
	system.Run();



	while(1)
	{	
		
	}



}


int main(int argc, char** argv)
{
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}