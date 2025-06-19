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

namespace Gs2::AdReward::Model
{
    class GS2ADREWARD_API FHistory final : public FGs2Object, public TSharedFromThis<FHistory>
    {
        TOptional<FString> ProviderValue;
        TOptional<FString> TransactionIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FHistory();
        FHistory(
            const FHistory& From
        );
        virtual ~FHistory() override = default;

        TSharedPtr<FHistory> WithProvider(const TOptional<FString> Provider);
        TSharedPtr<FHistory> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FHistory> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FHistory> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetProvider() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;


        static TSharedPtr<FHistory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FHistory, ESPMode::ThreadSafe> FHistoryPtr;
}