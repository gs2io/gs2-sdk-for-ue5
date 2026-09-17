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

#include "Core/Model/AcquireAction.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Model/VerifyAction.h"

namespace Gs2::Core::Domain::SpeculativeExecutor
{
    GS2CORE_API FString EscapeJsonStringContent(const FString& Value);

    GS2CORE_API Gs2::Core::Model::FAcquireActionPtr ApplyConfig(
        const Gs2::Core::Model::FAcquireActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    );

    GS2CORE_API Gs2::Core::Model::FConsumeActionPtr ApplyConfig(
        const Gs2::Core::Model::FConsumeActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    );

    GS2CORE_API Gs2::Core::Model::FVerifyActionPtr ApplyConfig(
        const Gs2::Core::Model::FVerifyActionPtr& Action,
        const TOptional<FString>& Key,
        const TOptional<FString>& Value
    );
}
