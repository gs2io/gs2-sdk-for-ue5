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
#include "../Model/Status.h"

namespace Gs2::SkillTree::Result
{
    class GS2SKILLTREE_API FReleaseByUserIdResult final : public TSharedFromThis<FReleaseByUserIdResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FReleaseByUserIdResult();
        FReleaseByUserIdResult(
            const FReleaseByUserIdResult& From
        );
        ~FReleaseByUserIdResult() = default;

        TSharedPtr<FReleaseByUserIdResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FReleaseByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReleaseByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReleaseByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReleaseByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FStatus> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FReleaseByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReleaseByUserIdResult, ESPMode::ThreadSafe> FReleaseByUserIdResultPtr;
}