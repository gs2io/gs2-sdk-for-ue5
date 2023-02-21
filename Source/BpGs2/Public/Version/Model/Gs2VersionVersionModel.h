/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Version/Domain/Model/Gs2VersionEzVersionModelDomain.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Gs2VersionVersionModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2VersionVersionModel
{
    GENERATED_BODY()

    Gs2::UE5::Version::Domain::Model::FEzVersionModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2VersionVersionModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FGs2VersionVersion WarningVersion = FGs2VersionVersion();
    UPROPERTY(BlueprintReadOnly)
    FGs2VersionVersion ErrorVersion = FGs2VersionVersion();
    UPROPERTY(BlueprintReadOnly)
    FString Scope = "";
    UPROPERTY(BlueprintReadOnly)
    FGs2VersionVersion CurrentVersion = FGs2VersionVersion();
    UPROPERTY(BlueprintReadOnly)
    bool NeedSignature = false;
};

inline FGs2VersionVersionModelValue EzVersionModelToFGs2VersionVersionModelValue(
    const Gs2::UE5::Version::Model::FEzVersionModelPtr Model
)
{
    FGs2VersionVersionModelValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.WarningVersion = Model->GetWarningVersion() ? EzVersionToFGs2VersionVersion(Model->GetWarningVersion()) : FGs2VersionVersion();
    Value.ErrorVersion = Model->GetErrorVersion() ? EzVersionToFGs2VersionVersion(Model->GetErrorVersion()) : FGs2VersionVersion();
    Value.Scope = Model->GetScope() ? *Model->GetScope() : "";
    Value.CurrentVersion = Model->GetCurrentVersion() ? EzVersionToFGs2VersionVersion(Model->GetCurrentVersion()) : FGs2VersionVersion();
    Value.NeedSignature = Model->GetNeedSignature() ? *Model->GetNeedSignature() : false;
    return Value;
}

inline Gs2::UE5::Version::Model::FEzVersionModelPtr FGs2VersionVersionModelValueToEzVersionModel(
    const FGs2VersionVersionModelValue Model
)
{
    return MakeShared<Gs2::UE5::Version::Model::FEzVersionModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithWarningVersion(FGs2VersionVersionToEzVersion(Model.WarningVersion))
        ->WithErrorVersion(FGs2VersionVersionToEzVersion(Model.ErrorVersion))
        ->WithScope(Model.Scope)
        ->WithCurrentVersion(FGs2VersionVersionToEzVersion(Model.CurrentVersion))
        ->WithNeedSignature(Model.NeedSignature);
}

UCLASS()
class BPGS2_API UGs2VersionVersionModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};