enum Estado {Susceptible, Infectado, Recuperado};
enum Contacto {contacto_directo, contacto_indirecto, contacto_cercano, contacto_aereo};
enum Direccion {dirigido, no_dirigido};
enum epidemia {Gripe, Colera, SARS, Gripe_aviar_y_porcina, Malaria, Chagas, Dengue, VIH, Hidatidosis, Sarampion};
enum TipoNodo{persona, Objeto, animal, agua};
struct TipoDeNodo{
    enum TipoNodo TipoNodo;
};

struct Vertices{
    enum Contacto contacto;
    enum Direccion direccion;
};

struct Gripe{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct Colera{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct SARS{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct Gripe_aviar_y_porcina{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct Malaria{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct Chagas{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct Dengue{
    struct TipoDeNodo TipoDeNodo;
    struct Vertices vertices;
    enum Estado Estado;
};

struct VIH{
   struct TipoDeNodo TipoDeNodo;
   struct Vertices vertices; 
    enum Estado Estado;
}; 

struct Hidatidosis{ 
   struct TipoDeNodo TipoDeNodo;
   struct Vertices vertices; 
    enum Estado Estado;
}; 

struct Sarampion{ 
   struct TipoDeNodo TipoDeNodo;
   struct Vertices vertices; 
   enum Estado Estado;
}; 
