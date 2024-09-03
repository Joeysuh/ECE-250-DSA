class playerlist{
    int playercounter;
    struct player
    {
        double x,y; // data
        player *next = nullptr; // node pointer
    };

    player *head; // head pointer
    public:
    playerlist(); // constructor
    ~playerlist(); // destructor
    // each function listed in manual:
    void SPAWN(double x, double y);
    void TIME(double t);
    void LUNCH();
    void NUM();
    void PRT(double distance);
    void OVER();
    
};