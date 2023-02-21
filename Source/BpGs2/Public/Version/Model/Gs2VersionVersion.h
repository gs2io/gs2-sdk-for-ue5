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

#include "Version/Model/Gs2VersionEzVersion.h"
#include "Gs2VersionVersion.generated.h"

USTRUCT(BlueprintType)
struct FGs2VersionVersion
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Major = 0;
    UPROPERTY(BlueprintReadWrite)
    int32 Minor = 0;
    UPROPERTY(BlueprintReadWrite)
    int32 Micro = 0;
};

inline FGs2VersionVersion EzVersionToFGs2VersionVersion(
    const Gs2::UE5::Version::Model::FEzVersionPtr Model
)
{
    FGs2VersionVersion Value;
    Value.Major = Model->GetMajor() ? *Model->GetMajor() : 0;
    Value.Minor = Model->GetMinor() ? *Model->GetMinor() : 0;
    Value.Micro = Model->GetMicro() ? *Model->GetMicro() : 0;
    return Value;
}

inline Gs2::UE5::Version::Model::FEzVersionPtr FGs2VersionVersionToEzVersion(
    const FGs2VersionVersion Model
)
{
    return MakeShared<Gs2::UE5::Version::Model::FEzVersion>()
        ->WithMajor(Model.Major)
        ->WithMinor(Model.Minor)
        ->WithMicro(Model.Micro);
}