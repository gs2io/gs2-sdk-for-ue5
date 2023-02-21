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
#include "Core/Gs2Domain.h"
#include "Gs2Region.generated.h"

UENUM(BlueprintType)
enum EGs2Region
{
    ApNorthEast1,
    UsEast1,
    EuWest1,
    ApSouthEast1,
};

inline Gs2::Core::Model::ERegion EGs2RegionToERegion(
    EGs2Region Region
)
{
    switch (Region)
    {
    case ApNorthEast1:
        return Gs2::Core::Model::ApNorthEast1;
    case UsEast1: 
        return Gs2::Core::Model::UsEast1;
    case EuWest1: 
        return Gs2::Core::Model::EuWest1;
    case ApSouthEast1: 
        return Gs2::Core::Model::ApSouthEast1;
    default: 
        return Gs2::Core::Model::ApNorthEast1;
    }
}
