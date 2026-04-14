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

namespace Gs2::Log::Model
{
    class GS2LOG_API FMetricModel final : public FGs2Object, public TSharedFromThis<FMetricModel>
    {
        TOptional<FString> NameValue;
        TOptional<FString> TypeValue;
        TSharedPtr<TArray<FString>> LabelsValue;

    public:
        FMetricModel();
        FMetricModel(
            const FMetricModel& From
        );
        virtual ~FMetricModel() override = default;

        TSharedPtr<FMetricModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FMetricModel> WithType(const TOptional<FString> Type);
        TSharedPtr<FMetricModel> WithLabels(const TSharedPtr<TArray<FString>> Labels);

        TOptional<FString> GetName() const;
        TOptional<FString> GetType() const;
        TSharedPtr<TArray<FString>> GetLabels() const;


        static TSharedPtr<FMetricModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMetricModel, ESPMode::ThreadSafe> FMetricModelPtr;
}