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
#include "../Model/RecoverValueTableMaster.h"

namespace Gs2::Stamina::Result
{
    class GS2STAMINA_API FDescribeRecoverValueTableMastersResult final : public TSharedFromThis<FDescribeRecoverValueTableMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FRecoverValueTableMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeRecoverValueTableMastersResult();
        FDescribeRecoverValueTableMastersResult(
            const FDescribeRecoverValueTableMastersResult& From
        );
        ~FDescribeRecoverValueTableMastersResult() = default;

        TSharedPtr<FDescribeRecoverValueTableMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FRecoverValueTableMaster>>> Items);
        TSharedPtr<FDescribeRecoverValueTableMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FRecoverValueTableMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeRecoverValueTableMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRecoverValueTableMastersResult, ESPMode::ThreadSafe> FDescribeRecoverValueTableMastersResultPtr;
}