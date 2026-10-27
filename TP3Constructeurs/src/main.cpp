
#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>

class BufferRAII {
private:
    std::unique_ptr<char[]> data;
    std::size_t taille;

public:
    // Constructeur
    explicit BufferRAII(std::size_t t)
        : data(t > 0 ? std::make_unique<char[]>(t) : nullptr),
          taille(t) {
        std::fill_n(data.get(), taille, 0);

        std::cout << "Buffer cree" << std::endl;
    }

    // Accesseurs
    char* get() const {
        return data.get();
    }

    std::size_t size() const {
        return taille;
    }
};

class CompteSecure {
private:
    double solde;

public:
    explicit CompteSecure(double soldeInitial)
        : solde(soldeInitial) {
        if (soldeInitial < 0) {
            throw std::invalid_argument(
                "Solde initial negatif"
            );
        }
    }

    void afficher() const {
        std::cout << "Solde : " << solde << std::endl;
    }
};

int main() {
    BufferRAII b(256);

    std::cout << "Buffer de " << b.size()
              << " octets alloue" << std::endl;

    try {
        CompteSecure c(500);
        c.afficher();

        CompteSecure c2(-100);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
