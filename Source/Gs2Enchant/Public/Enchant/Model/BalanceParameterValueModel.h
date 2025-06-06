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

namespace Gs2::Enchant::Model
{
    class GS2ENCHANT_API FBalanceParameterValueModel final : public FGs2Object, public TSharedFromThis<FBalanceParameterValueModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

    public:
        FBalanceParameterValueModel();
        FBalanceParameterValueModel(
            const FBalanceParameterValueModel& From
        );
        virtual ~FBalanceParameterValueModel() override = default;

        TSharedPtr<FBalanceParameterValueModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FBalanceParameterValueModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;


        static TSharedPtr<FBalanceParameterValueModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBalanceParameterValueModel, ESPMode::ThreadSafe> FBalanceParameterValueModelPtr;
}