#include <cstdio>
#include <chrono>

class TimerClass {
  std::chrono::steady_clock::time_point timestamp;
  bool valid = true;
  char* name;
  const size_t name_size = 201;

public:
    TimerClass(const char* name)
        : timestamp(std::chrono::steady_clock::now()) {
      this->name = new char[name_size];
      strncpy(this->name, name, name_size);
	}

    ~TimerClass() {
      if(valid) {
        auto now = std::chrono::steady_clock::now();

        auto age = std::chrono::duration<double>(now - timestamp).count();
        printf("The age the %s timer is %f.\n", name, age);
      }
      delete[] name;
    }

    TimerClass(const TimerClass& other): timestamp(other.timestamp) { 
	    name = new char[name_size];
      strncpy(this->name, other.name, other.name_size);
    }
    TimerClass& operator=(const TimerClass& other) {
      if(this == &other)
        return *this;
       
      timestamp = other.timestamp;
      delete[] name;
      name = new char[name_size];
      strncpy(this->name, other.name, name_size);
    }
    TimerClass(TimerClass&& other) noexcept
        : timestamp(other.timestamp)
        , valid(other.valid)
    , name(other.name){
      other.valid = false;
      other.name = nullptr;
    }
    TimerClass& operator=(TimerClass&& other) noexcept {
      if(this == &other)
        return *this;
      timestamp = other.timestamp;
      valid = other.valid;
      delete[] name;
      name = other.name;

      other.valid = false;
      other.name = nullptr;
    }
};

void calculate(TimerClass a) {
  _sleep(40);
}

int main() {
  TimerClass timer("out年后");
  calculate(std::move(timer));
  return 0;
}