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

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FPurchaseCount final : public FGs2Object, public TSharedFromThis<FPurchaseCount>
    {
        TOptional<FString> NameValue;
        TOptional<int32> CountValue;

    public:
        FPurchaseCount();
        FPurchaseCount(
            const FPurchaseCount& From
        );
        virtual ~FPurchaseCount() override = default;

        TSharedPtr<FPurchaseCount> WithName(const TOptional<FString> Name);
        TSharedPtr<FPurchaseCount> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetName() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FPurchaseCount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPurchaseCount, ESPMode::ThreadSafe> FPurchaseCountPtr;
}