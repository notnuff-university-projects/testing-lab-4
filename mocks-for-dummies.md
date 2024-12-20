1. mock vs fake:

* Fake objects have working implementations, but usually take some shortcut 
(perhaps to make the operations less expensive), 
which makes them not suitable for production. 
An in-memory file system would be an example of a fake.

* Mocks are objects pre-programmed with expectations, 
which form a specification of the calls 
they are expected to receive.

2. gMock is about:

* a design tool, for it lets you experiment with your interface
design early and often. More iterations lead to better designs!

* a testing tool to cut your tests’ outbound 
dependencies and probe the interaction between 
your module and its collaborators.

3. case study: Mock Turtles:

* Dependency Injection: 
the right thing to do: 
instead of having your application talk to 
the system API directly, 
wrap the API in an interface (say, Turtle) 
and code to that interface:


    class Turtle {
    ...
    virtual ~Turtle() {}
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
    };

* Mocking the Turtle with gtest:


    class MockTurtle : public Turtle {
    public:
    ...
    MOCK_METHOD(void, PenUp, (), (override));
    MOCK_METHOD(void, PenDown, (), (override));
    MOCK_METHOD(void, Forward, (int distance), (override));
    MOCK_METHOD(void, Turn, (int degrees), (override));
    MOCK_METHOD(void, GoTo, (int x, int y), (override));
    MOCK_METHOD(int, GetX, (), (const, override));
    MOCK_METHOD(int, GetY, (), (const, override));
    };

