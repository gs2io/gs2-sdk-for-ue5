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
#include "../Model/AcquireAction.h"
#include "../Model/Status.h"

namespace Gs2::Idle::Result
{
    class GS2IDLE_API FPredictionResult final : public TSharedFromThis<FPredictionResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ItemsValue;
        TSharedPtr<Model::FStatus> StatusValue;
        
    public:
        
        FPredictionResult();
        FPredictionResult(
            const FPredictionResult& From
        );
        ~FPredictionResult() = default;

        TSharedPtr<FPredictionResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> Items);
        TSharedPtr<FPredictionResult> WithStatus(const TSharedPtr<Model::FStatus> Status);

        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetItems() const;
        TSharedPtr<Model::FStatus> GetStatus() const;

        static TSharedPtr<FPredictionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPredictionResult, ESPMode::ThreadSafe> FPredictionResultPtr;
}