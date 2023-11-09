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
#include "Version/Domain/Model/Gs2VersionEzAcceptVersionGameSessionDomain.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Core/BpGs2Constant.h"
#include "Gs2VersionAcceptVersion.generated.h"

USTRUCT(BlueprintType)
struct FGs2VersionOwnAcceptVersion
{
    GENERATED_BODY()

    Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2VersionAcceptVersionValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString VersionName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2VersionVersion Version = FGs2VersionVersion();
};

inline FGs2VersionAcceptVersionValue EzAcceptVersionToFGs2VersionAcceptVersionValue(
    const Gs2::UE5::Version::Model::FEzAcceptVersionPtr Model
)
{
    FGs2VersionAcceptVersionValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionAcceptVersionFunctionLibrary::EzAcceptVersionToFGs2VersionAcceptVersionValue] Model parameter specification is missing."))
        return Value;
    }
    Value.VersionName = Model->GetVersionName() ? *Model->GetVersionName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Version = Model->GetVersion() ? EzVersionToFGs2VersionVersion(Model->GetVersion()) : FGs2VersionVersion();
    return Value;
}

inline Gs2::UE5::Version::Model::FEzAcceptVersionPtr FGs2VersionAcceptVersionValueToEzAcceptVersion(
    const FGs2VersionAcceptVersionValue Model
)
{
    return MakeShared<Gs2::UE5::Version::Model::FEzAcceptVersion>()
        ->WithVersionName(Model.VersionName)
        ->WithUserId(Model.UserId)
        ->WithVersion(FGs2VersionVersionToEzVersion(Model.Version));
}

UCLASS()
class BPGS2_API UGs2VersionAcceptVersionFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};