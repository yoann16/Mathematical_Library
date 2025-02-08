#pragma once
#include "Outils_Math.h"
#include <gtest/gtest.h>
using namespace Mathematical_library;

class MathematicalPropertiesTest : public ::testing::Test
{
protected:
	// Vecteurs de test
	VectorND<double, 3> v1{ 1.0, 2.0, 3.0 };
	VectorND<double, 3> v2{ 4.0, 5.0, 6.0 };
	VectorND<double, 3> v3{ 7.0, 8.0, 9.0 };

	// Matrices de test
	Matrix<double, 3, 3> m1{
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0},
		{7.0, 8.0, 9.0}
	};
	Matrix<double, 3, 3> m2{
		{9.0, 8.0, 7.0},
		{6.0, 5.0, 4.0},
		{3.0, 2.0, 1.0}
	};
};

// Tests des propriétés vectorielles
TEST_F(MathematicalPropertiesTest, VectorBasicProperties)
{
	// Propriété commutative de l'addition
	EXPECT_EQ(v1 + v2, v2 + v1);

	// Produit scalaire commutatif
	EXPECT_NEAR(DotProduct(v1, v2), DotProduct(v2, v1), 1e-10);
}

// Tests du produit scalaire
TEST_F(MathematicalPropertiesTest, DotProductProperties)
{
	// Produit scalaire avec vecteur nul
	VectorND<double, 3> zeroVec{ 0.0, 0.0, 0.0 };
	EXPECT_NEAR(DotProduct(v1, zeroVec), 0.0, 1e-10);

	// Distributivité du produit scalaire
	EXPECT_NEAR(DotProduct(v1 + v2, v3),
		DotProduct(v1, v3) + DotProduct(v2, v3),
		1e-10);
}

// Tests de la norme vectorielle
TEST_F(MathematicalPropertiesTest, NormProperties)
{
	// Norme toujours positive
	EXPECT_GE(Norm(v1), 0.0);

	// Norme du vecteur normalisé
	VectorND<double, 3> normalized = Normalize(v1);
	EXPECT_NEAR(Norm(normalized), 1.0, 1e-10);

	// Vecteur nul ne peut pas être normalisé
	VectorND<double, 3> zeroVec{ 0.0, 0.0, 0.0 };
	EXPECT_THROW(Normalize(zeroVec), std::runtime_error);
}

// Tests du produit vectoriel
TEST_F(MathematicalPropertiesTest, CrossProductProperties)
{
	// Antisymétrie du produit vectoriel
	VectorND<double, 3> crossProd1 = CrossProduct(v1, v2);
	VectorND<double, 3> crossProd2 = CrossProduct(v2, v1);
	EXPECT_EQ(crossProd1, -crossProd2);

	// Orthogonalité du produit vectoriel
	EXPECT_NEAR(DotProduct(crossProd1, v1), 0.0, 1e-10);
	EXPECT_NEAR(DotProduct(crossProd1, v2), 0.0, 1e-10);
}

// Tests des propriétés matricielles
TEST_F(MathematicalPropertiesTest, MatrixBasicProperties)
{
	// Commutativité de l'addition
	EXPECT_EQ(m1 + m2, m2 + m1);

	// Multiplication par un scalaire
	double scalar = 2.0;
	Matrix<double, 3, 3> scaledM1 = m1 * scalar;
	Matrix<double, 3, 3> scaledM2 = scalar * m1;
	EXPECT_EQ(scaledM1, scaledM2);
}

// Tests de multiplication matricielle
TEST_F(MathematicalPropertiesTest, MatrixMultiplicationProperties)
{
	// Création d'une matrice identité
	Matrix<double, 3, 3> identityMatrix
	{
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}
	};

	// Multiplication par la matrice identité
	Matrix<double, 3, 3> m1TimesIdentity = m1 * identityMatrix;
	EXPECT_EQ(m1TimesIdentity, m1);

	// Vecteur unitaire
	VectorND<double, 3> unitVec{ 1.0, 0.0, 0.0 };
	VectorND<double, 3> transformedVec = m1 * unitVec;

	// Vérification que le résultat correspond à la première colonne
	for (size_t i = 0; i < 3; ++i) 
	{
		EXPECT_NEAR(transformedVec[i], m1.getCell(i, 0), 1e-10);
	}
}

// Tests de la normalisation vectorielle
TEST_F(MathematicalPropertiesTest, VectorNormalizationProperties)
{
	// Préservation de la direction lors de la normalisation
	VectorND<double, 3> normalized = Normalize(v1);

	// Vérification de la conservation de l'angle
	double originalDot = DotProduct(v1, v2);
	double normalizedDot = DotProduct(normalized, Normalize(v2));

	EXPECT_NEAR(originalDot / (Norm(v1) * Norm(v2)),
		normalizedDot,
		1e-10);
}

// Tests des opérations complexes
TEST_F(MathematicalPropertiesTest, ComplexOperations)
{
	// Associativité du produit matriciel : (A * B) * C = A * (B * C)
	Matrix<double, 3, 3> m3
	{
		{2.0, 3.0, 4.0},
		{5.0, 6.0, 7.0},
		{8.0, 9.0, 10.0}
	};

	auto left = (m1 * m2) * m3;
	auto right = m1 * (m2 * m3);

	for (size_t i = 0; i < 3; ++i) 
	{
		for (size_t j = 0; j < 3; ++j) 
		{
			EXPECT_NEAR(left.getCell(i, j), right.getCell(i, j), 1e-10);
		}
	}
}

// Tests des différentes dimensions de vecteurs
TEST_F(MathematicalPropertiesTest, MultiDimensionalVectors)
{
	// Test avec un vecteur 7D
	VectorND<double, 7> v7D;
	for (size_t i = 0; i < 7; ++i) 
	{
		v7D[i] = i + 1;
	}

	// Vérification de la somme des éléments
	double sum = 0.0;
	for (size_t i = 0; i < 7; ++i) 
	{
		sum += v7D[i];
	}
	EXPECT_NEAR(sum, 28.0, 1e-10);
}