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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FUnleashMaterialSelection final : public FGs2Object, public TSharedFromThis<FUnleashMaterialSelection>
    {
        TOptional<FString> NameValue;
        TSharedPtr<TArray<FString>> ItemSetIdsValue;

    public:
        FUnleashMaterialSelection();
        FUnleashMaterialSelection(
            const FUnleashMaterialSelection& From
        );
        virtual ~FUnleashMaterialSelection() override = default;

        TSharedPtr<FUnleashMaterialSelection> WithName(const TOptional<FString> Name);
        TSharedPtr<FUnleashMaterialSelection> WithItemSetIds(const TSharedPtr<TArray<FString>> ItemSetIds);

        TOptional<FString> GetName() const;
        TSharedPtr<TArray<FString>> GetItemSetIds() const;


        static TSharedPtr<FUnleashMaterialSelection> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnleashMaterialSelection, ESPMode::ThreadSafe> FUnleashMaterialSelectionPtr;
}