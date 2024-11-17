#pragma once


//TODO: Add source control to the modifier to identify where the modifier is coming from (e.g. building, upgrade, etc.)
class modifier {
public:
	double multiplier;
	double additive;

	modifier(double& multiplier, double& additive) : multiplier(multiplier), additive(additive) {}
};