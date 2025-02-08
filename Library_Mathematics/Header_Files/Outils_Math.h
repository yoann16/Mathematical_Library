#pragma once
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "Array.h"

namespace Mathematical_library
{
    // Fonction utilitaire pour la comparaison des nombres flottants
    template<typename T>
    bool nearly_equal(T a, T b, T epsilon = 1e-10) {
        return std::abs(a - b) <= epsilon;
    }

    // Déclarations anticipées
    template<typename T, size_t N> class VectorND;
    template<typename T, size_t L, size_t C> class Matrix;

    // Classe VectorND à N dimensions
    template<typename T, size_t N>
    class VectorND : public Array<T, N> {
    public:
        // Constructeurs
        VectorND() : Array<T, N>() {}

        // Constructeur par liste d'initialisation
        VectorND(std::initializer_list<T> list) : Array<T, N>(list) {
            if (list.size() != N) {
                throw std::runtime_error("Taille incorrecte pour l'initialisation du vecteur");
            }
        }

        // Constructeur de copie
        VectorND(const VectorND& other) : Array<T, N>(other) {}

        // Opérations vectorielles
        VectorND operator+(const VectorND& other) const {
            VectorND result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = (*this)[i] + other[i];
            }
            return result;
        }

        VectorND operator*(const T& scalar) const {
            VectorND result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = (*this)[i] * scalar;
            }
            return result;
        }

        // Opérateur pour multiplication scalaire dans l'autre sens
        friend VectorND operator*(const T& scalar, const VectorND& v) {
            return v * scalar;
        }

        // Opérateur de négation pour le produit vectoriel
        VectorND operator-() const {
            VectorND result;
            for (size_t i = 0; i < N; ++i) {
                result[i] = -(*this)[i];
            }
            return result;
        }

        // Getter statique pour la dimension
        static constexpr size_t getDimension() { return N; }
    };

    // Classe Matrix à L×C dimensions
    template<typename T, size_t L, size_t C>
    class Matrix {
    private:
        Array<T, L* C> data;  // Stockage linéaire dans un tableau 1D

    public:
        // Constructeur par défaut
        Matrix() : data() {}  // Initialise tous les éléments à zéro

        // Constructeur par liste d'initialisation
        Matrix(std::initializer_list<std::initializer_list<T>> list) : data() {
            if (list.size() != L) {
                throw std::runtime_error("Nombre de lignes incorrect");
            }
            size_t row = 0;
            for (const auto& rowList : list) {
                if (rowList.size() != C) {
                    throw std::runtime_error("Nombre de colonnes incorrect");
                }
                size_t col = 0;
                for (const auto& val : rowList) {
                    getCell(row, col++) = val;
                }
                row++;
            }
        }

        // Accès aux éléments avec vérification des bornes
        T& getCell(size_t row, size_t col) {
            if (row >= L || col >= C) throw std::out_of_range("Index hors limites");
            return data[row * C + col];
        }

        const T& getCell(size_t row, size_t col) const {
            if (row >= L || col >= C) throw std::out_of_range("Index hors limites");
            return data[row * C + col];
        }

        // Méthodes statiques de dimension
        static constexpr size_t getRows() { return L; }
        static constexpr size_t getCols() { return C; }

        // Opérations mathématiques de base
        Matrix operator+(const Matrix& other) const {
            Matrix result;
            for (size_t i = 0; i < L * C; ++i) {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        Matrix operator*(const T& scalar) const {
            Matrix result;
            for (size_t i = 0; i < L * C; ++i) {
                result.data[i] = data[i] * scalar;
            }
            return result;
        }

        // Opérateur de comparaison
        bool operator==(const Matrix& other) const {
            for (size_t i = 0; i < L * C; ++i) {
                if (!nearly_equal(data[i], other.data[i])) return false;
            }
            return true;
        }

        // Opérateur de différence
        bool operator!=(const Matrix& other) const {
            return !(*this == other);
        }
    };

    // Produit scalaire-matrice (scalaire * matrice)
    template<typename T, size_t L, size_t C>
    Matrix<T, L, C> operator*(const T& scalar, const Matrix<T, L, C>& m) {
        Matrix<T, L, C> result;
        for (size_t i = 0; i < L; ++i) {
            for (size_t j = 0; j < C; ++j) {
                result.getCell(i, j) = scalar * m.getCell(i, j);
            }
        }
        return result;
    }

    // Produit scalaire pour vecteurs de même dimension
    template<typename T, size_t N>
    T DotProduct(const VectorND<T, N>& v1, const VectorND<T, N>& v2) {
        T result = T();
        for (size_t i = 0; i < N; ++i) {
            result = std::fma(v1[i], v2[i], result);
        }
        return nearly_equal(result, T(0)) ? T(0) : result;
    }

    // Norme d'un vecteur
    template<typename T, size_t N>
    double Norm(const VectorND<T, N>& v) {
        return std::sqrt(static_cast<double>(DotProduct(v, v)));
    }

    // Normalisation d'un vecteur
    template<typename T, size_t N>
    VectorND<T, N> Normalize(const VectorND<T, N>& v) {
        double norm = Norm(v);
        if (nearly_equal(norm, 0.0))
            throw std::runtime_error("Cannot normalize zero vector");

        VectorND<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = static_cast<T>(v[i] / norm);
        }
        return result;
    }

    // Produit vectoriel (uniquement pour les vecteurs 3D)
    template<typename T>
    VectorND<T, 3> CrossProduct(const VectorND<T, 3>& v1, const VectorND<T, 3>& v2) {
        VectorND<T, 3> result;
        result[0] = v1[1] * v2[2] - v1[2] * v2[1];
        result[1] = v1[2] * v2[0] - v1[0] * v2[2];
        result[2] = v1[0] * v2[1] - v1[1] * v2[0];

        for (size_t i = 0; i < 3; ++i) {
            if (nearly_equal(result[i], T(0))) {
                result[i] = T(0);
            }
        }

        return result;
    }

    // Produit matrice-vecteur
    template<typename T, size_t L, size_t C>
    VectorND<T, L> operator*(const Matrix<T, L, C>& m, const VectorND<T, C>& v) {
        VectorND<T, L> result;
        for (size_t i = 0; i < L; ++i) {
            T sum = T();
            for (size_t j = 0; j < C; ++j) {
                sum = std::fma(m.getCell(i, j), v[j], sum);
            }
            result[i] = nearly_equal(sum, T(0)) ? T(0) : sum;
        }
        return result;
    }

    // Produit matriciel
    template<typename T, size_t L1, size_t C1, size_t C2>
    Matrix<T, L1, C2> operator*(const Matrix<T, L1, C1>& m1, const Matrix<T, C1, C2>& m2) {
        Matrix<T, L1, C2> result;
        for (size_t i = 0; i < L1; ++i) {
            for (size_t j = 0; j < C2; ++j) {
                T sum = T();
                for (size_t k = 0; k < C1; ++k) {
                    sum = std::fma(m1.getCell(i, k), m2.getCell(k, j), sum);
                }
                result.getCell(i, j) = nearly_equal(sum, T(0)) ? T(0) : sum;
            }
        }
        return result;
    }
}