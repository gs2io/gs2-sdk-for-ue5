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

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FAttribute final : public FGs2Object, public TSharedFromThis<FAttribute>
    {
        TOptional<FString> NameValue;
        TOptional<int32> ValueValue;

    public:
        FAttribute();
        FAttribute(
            const FAttribute& From
        );
        virtual ~FAttribute() override = default;

        TSharedPtr<FAttribute> WithName(const TOptional<FString> Name);
        TSharedPtr<FAttribute> WithValue(const TOptional<int32> Value);

        TOptional<FString> GetName() const;
        TOptional<int32> GetValue() const;
        FString GetValueString() const;


        static TSharedPtr<FAttribute> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAttribute, ESPMode::ThreadSafe> FAttributePtr;
}