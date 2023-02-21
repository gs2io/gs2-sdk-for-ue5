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

namespace Gs2::Core::Model
{
    /**
     * 
    */
    enum ERegion
    {
        ApNorthEast1 = 0,
        UsEast1 = 1,
        EuWest1 = 2,
        ApSouthEast1 = 3,
    };

    inline FString ToString(ERegion Region)
    {
        switch (Region)
        {
            case ApNorthEast1: 
                return "ap-northeast-1";
            case UsEast1: 
                return "us-east-1";
            case EuWest1: 
                return "eu-west-1";
            case ApSouthEast1: 
                return "ap-southeast-1";
            default: ;
        }
        return "";
    }
}