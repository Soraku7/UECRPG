// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/UnitComponentInterface.h"


// Add default functionality here for any IUnitComponentInterface functions that are not pure virtual.
void IUnitComponentInterface::DoInitialize()
{
}

void IUnitComponentInterface::DoReset()
{
}

void IUnitComponentInterface::DoDispose()
{
}

ACharacterBase* IUnitComponentInterface::GetCompOwner() const
{
	return nullptr;
}
