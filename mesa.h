#include <iostream>

class Mesa {
private:
    int nro_mesa, can_sillas, ubic;
    char * desc;
public:
    Mesa(int n_nro_mesa);
    Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, char * n_desc);
    Mesa(int n_nro_mesa, int n_can_sillas, int n_ubic, std::string n_desc);
    ~Mesa();
    int get_nro_mesa();
    int get_can_sillas();
    int get_ubic();
    std::string get_desc();
    void set_nro_mesa(int n_nro_mesa);
    void set_can_sillas(int n_can_sillas);
    void set_ubic(int n_ubic);
    void set_desc(char * n_desc);
    void set_desc(std::string n_desc);
};
