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

#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Version/Model/Gs2VersionVersion.h"
#include "Gs2VersionTargetVersion.generated.h"

USTRUCT(BlueprintType)
struct FGs2VersionTargetVersion
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString VersionName = "";
    UPROPERTY(BlueprintReadWrite)
    FString Body = "";
    UPROPERTY(BlueprintReadWrite)
    FString Signature = "";
    UPROPERTY(BlueprintReadWrite)
    FGs2VersionVersion Version = FGs2VersionVersion();
};

inline FGs2VersionTargetVersion EzTargetVersionToFGs2VersionTargetVersion(
    const Gs2::UE5::Version::Model::FEzTargetVersionPtr Model
)
{
    FGs2VersionTargetVersion Value;
    Value.VersionName = Model->GetVersionName() ? *Model->GetVersionName() : "";
    Value.Version = Model->GetVersion() ? EzVersionToFGs2VersionVersion(Model->GetVersion()) : FGs2VersionVersion();
    Value.Body = Model->GetBody() ? *Model->GetBody() : "";
    Value.Signature = Model->GetSignature() ? *Model->GetSignature() : "";
    return Value;
}

inline Gs2::UE5::Version::Model::FEzTargetVersionPtr FGs2VersionTargetVersionToEzTargetVersion(
    const FGs2VersionTargetVersion Model
)
{
    return MakeShared<Gs2::UE5::Version::Model::FEzTargetVersion>()
        ->WithVersionName(Model.VersionName)
        ->WithVersion(FGs2VersionVersionToEzVersion(Model.Version))
        ->WithBody(Model.Body)
        ->WithSignature(Model.Signature);
}