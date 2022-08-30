#ifndef FPSLIMITER_H
#define FPSLIMITER_H

	class FpsLimiter
	{
	public:
		FpsLimiter();
		~FpsLimiter();

		// Sets the desired max FPS
		void setMaxFPS(float maxFPS);

		void begin();

		// end() will return the current FPS as a float
		float end();
	private:
		// Calculates the current FPS
		void calculateFPS();

		// Variables
		float _fps;
		float _maxFPS;
		float _frameTime;
		unsigned int _startTicks;
	};
#endif
