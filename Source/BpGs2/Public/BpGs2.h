#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBpGs2Module : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
