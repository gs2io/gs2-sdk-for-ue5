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
#include "../Model/StateMachineMaster.h"

namespace Gs2::StateMachine::Result
{
    class GS2STATEMACHINE_API FDescribeStateMachineMastersResult final : public TSharedFromThis<FDescribeStateMachineMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FStateMachineMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeStateMachineMastersResult();
        FDescribeStateMachineMastersResult(
            const FDescribeStateMachineMastersResult& From
        );
        ~FDescribeStateMachineMastersResult() = default;

        TSharedPtr<FDescribeStateMachineMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FStateMachineMaster>>> Items);
        TSharedPtr<FDescribeStateMachineMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FStateMachineMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeStateMachineMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStateMachineMastersResult, ESPMode::ThreadSafe> FDescribeStateMachineMastersResultPtr;
}