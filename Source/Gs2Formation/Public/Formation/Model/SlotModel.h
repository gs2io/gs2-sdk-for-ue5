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

namespace Gs2::Formation::Model
{
    class GS2FORMATION_API FSlotModel final : public TSharedFromThis<FSlotModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> PropertyRegexValue;
        TOptional<FString> MetadataValue;

    public:
        FSlotModel();
        FSlotModel(
            const FSlotModel& From
        );
        ~FSlotModel() = default;

        TSharedPtr<FSlotModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FSlotModel> WithPropertyRegex(const TOptional<FString> PropertyRegex);
        TSharedPtr<FSlotModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;
        TOptional<FString> GetPropertyRegex() const;
        TOptional<FString> GetMetadata() const;


        static TSharedPtr<FSlotModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSlotModel, ESPMode::ThreadSafe> FSlotModelPtr;
}