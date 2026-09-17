/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
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
#include "Math/BigInt.h"

namespace Gs2::Core::Util
{
    GS2CORE_API bool TryApplyServerRate(
        int64 Count,
        double Rate,
        int64& Value
    );

    GS2CORE_API bool TryApplyServerRate(
        int64 Count,
        const TBigInt<1024, false>& Rate,
        int64& Value
    );

    GS2CORE_API bool TryApplyServerRate(
        int32 Count,
        double Rate,
        int32& Value
    );

    GS2CORE_API bool TryApplyServerRate(
        int32 Count,
        const TBigInt<1024, false>& Rate,
        int32& Value
    );
}
