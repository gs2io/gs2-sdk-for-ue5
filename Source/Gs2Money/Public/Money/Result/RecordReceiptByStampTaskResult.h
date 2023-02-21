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
#include "../Model/Receipt.h"

namespace Gs2::Money::Result
{
    class GS2MONEY_API FRecordReceiptByStampTaskResult final : public TSharedFromThis<FRecordReceiptByStampTaskResult>
    {
        TSharedPtr<Model::FReceipt> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FRecordReceiptByStampTaskResult();
        FRecordReceiptByStampTaskResult(
            const FRecordReceiptByStampTaskResult& From
        );
        ~FRecordReceiptByStampTaskResult() = default;

        TSharedPtr<FRecordReceiptByStampTaskResult> WithItem(const TSharedPtr<Model::FReceipt> Item);
        TSharedPtr<FRecordReceiptByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FReceipt> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FRecordReceiptByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRecordReceiptByStampTaskResult, ESPMode::ThreadSafe> FRecordReceiptByStampTaskResultPtr;
}