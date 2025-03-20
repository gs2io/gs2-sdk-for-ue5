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

namespace Gs2::Exchange::Model
{
    class GS2EXCHANGE_API FLogCost final : public FGs2Object, public TSharedFromThis<FLogCost>
    {
        TOptional<double> BaseValue;
        TSharedPtr<TArray<double>> AddsValue;
        TSharedPtr<TArray<double>> SubsValue;

    public:
        FLogCost();
        FLogCost(
            const FLogCost& From
        );
        virtual ~FLogCost() override = default;

        TSharedPtr<FLogCost> WithBase(const TOptional<double> Base);
        TSharedPtr<FLogCost> WithAdds(const TSharedPtr<TArray<double>> Adds);
        TSharedPtr<FLogCost> WithSubs(const TSharedPtr<TArray<double>> Subs);

        TOptional<double> GetBase() const;
        FString GetBaseString() const;
        TSharedPtr<TArray<double>> GetAdds() const;
        TSharedPtr<TArray<double>> GetSubs() const;


        static TSharedPtr<FLogCost> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLogCost, ESPMode::ThreadSafe> FLogCostPtr;
}