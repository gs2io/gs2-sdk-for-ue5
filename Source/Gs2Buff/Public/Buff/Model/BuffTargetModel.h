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
#include "BuffTargetGrn.h"

namespace Gs2::Buff::Model
{
    class GS2BUFF_API FBuffTargetModel final : public Gs2Object, public TSharedFromThis<FBuffTargetModel>
    {
        TOptional<FString> TargetModelNameValue;
        TOptional<FString> TargetFieldNameValue;
        TSharedPtr<TArray<TSharedPtr<FBuffTargetGrn>>> ConditionGrnsValue;
        TOptional<float> RateValue;

    public:
        FBuffTargetModel();
        FBuffTargetModel(
            const FBuffTargetModel& From
        );
        virtual ~FBuffTargetModel() override = default;

        TSharedPtr<FBuffTargetModel> WithTargetModelName(const TOptional<FString> TargetModelName);
        TSharedPtr<FBuffTargetModel> WithTargetFieldName(const TOptional<FString> TargetFieldName);
        TSharedPtr<FBuffTargetModel> WithConditionGrns(const TSharedPtr<TArray<TSharedPtr<FBuffTargetGrn>>> ConditionGrns);
        TSharedPtr<FBuffTargetModel> WithRate(const TOptional<float> Rate);

        TOptional<FString> GetTargetModelName() const;
        TOptional<FString> GetTargetFieldName() const;
        TSharedPtr<TArray<TSharedPtr<FBuffTargetGrn>>> GetConditionGrns() const;
        TOptional<float> GetRate() const;
        FString GetRateString() const;


        static TSharedPtr<FBuffTargetModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBuffTargetModel, ESPMode::ThreadSafe> FBuffTargetModelPtr;
}