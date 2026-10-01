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
#include "Core/Model/Gs2Error.h"

namespace Gs2::Core::Model
{
    typedef TFunction<FGs2ErrorPtr(const FString& Method, FGs2ErrorPtr Error)> FGs2ServiceErrorResolver;

    class GS2CORE_API FGs2ErrorResolver
    {
    public:
        static bool Register(const FString& Service, FGs2ServiceErrorResolver Resolver);
        static FGs2ErrorPtr Resolve(const FString& Service, const FString& Method, FGs2ErrorPtr Error);
        static FGs2ErrorPtr ResolveAction(const FString& Action, FGs2ErrorPtr Error);
        static FGs2ErrorPtr ResolveJobScript(const FString& ScriptId, FGs2ErrorPtr Error);
        static bool HasCode(const FGs2ErrorPtr& Error, const FString& Code);
    };
}
