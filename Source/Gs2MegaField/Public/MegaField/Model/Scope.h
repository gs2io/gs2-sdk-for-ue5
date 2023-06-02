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
#include "Core/Gs2Object.h"

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FScope final : public Gs2Object, public TSharedFromThis<FScope>
    {
        TOptional<FString> LayerNameValue;
        TOptional<float> RValue;
        TOptional<int32> LimitValue;

    public:
        FScope();
        FScope(
            const FScope& From
        );
        virtual ~FScope() override = default;

        TSharedPtr<FScope> WithLayerName(const TOptional<FString> LayerName);
        TSharedPtr<FScope> WithR(const TOptional<float> R);
        TSharedPtr<FScope> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetLayerName() const;
        TOptional<float> GetR() const;
        FString GetRString() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;


        static TSharedPtr<FScope> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScope, ESPMode::ThreadSafe> FScopePtr;
}