#ifndef LIFT_HPP
#define LIFT_HPP

#include <exception>

class OverloadException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ПОМИЛКА: Перевищено граничне навантаження. Рух заблоковано.";
    }
};

enum GeneralState {
	STATE_IDLE,
	STATE_CALLED,
	STATE_MOVING
};

enum EngineState {
	ENGINE_OFF,
	ENGINE_UP,
	ENGINE_DOWN
};

enum DoorState {
	DOORS_OPEN,
	DOORS_CLOSED
};

class Lift {
private:
	GeneralState gState;
	EngineState eState;
	DoorState dState;
	int currentFloor;
	int targetFloor;
	double currentLoad;

	static const int MIN_FLOOR = 1;
	static const int MAX_FLOOR = 24;

	static const double MAX_LOAD;

	void updateEngineState();
	bool isLoadValid();

public:
	Lift();
	void Reset();

	void StartCall(int destinationFloor);
	void EndCall();

	void LoadCabin(double load);

	void Start(int destinationFloor);
	void Stop();

	GeneralState GetGeneralState() const;
	EngineState GetEngineState() const;
	DoorState GetDoorState() const;
	int GetCurrentFloor() const;
	int GetTargetFloor() const;
	double GetCurrentLoad() const;

	const char* GetGeneralStateName() const;
	const char* GetEngineStateName() const;
	const char* GetDoorStateName() const;
};

#endif
