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
#include "VerifyReceiptEvent.h"
#include "DepositEvent.h"
#include "WithdrawEvent.h"
#include "RefundEvent.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FEvent final : public Gs2Object, public TSharedFromThis<FEvent>
    {
        TOptional<FString> EventIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> EventTypeValue;
        TSharedPtr<FVerifyReceiptEvent> VerifyReceiptEventValue;
        TSharedPtr<FDepositEvent> DepositEventValue;
        TSharedPtr<FWithdrawEvent> WithdrawEventValue;
        TSharedPtr<FRefundEvent> RefundEventValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FEvent();
        FEvent(
            const FEvent& From
        );
        virtual ~FEvent() override = default;

        TSharedPtr<FEvent> WithEventId(const TOptional<FString> EventId);
        TSharedPtr<FEvent> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEvent> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEvent> WithEventType(const TOptional<FString> EventType);
        TSharedPtr<FEvent> WithVerifyReceiptEvent(const TSharedPtr<FVerifyReceiptEvent> VerifyReceiptEvent);
        TSharedPtr<FEvent> WithDepositEvent(const TSharedPtr<FDepositEvent> DepositEvent);
        TSharedPtr<FEvent> WithWithdrawEvent(const TSharedPtr<FWithdrawEvent> WithdrawEvent);
        TSharedPtr<FEvent> WithRefundEvent(const TSharedPtr<FRefundEvent> RefundEvent);
        TSharedPtr<FEvent> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEvent> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetEventId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetEventType() const;
        TSharedPtr<FVerifyReceiptEvent> GetVerifyReceiptEvent() const;
        TSharedPtr<FDepositEvent> GetDepositEvent() const;
        TSharedPtr<FWithdrawEvent> GetWithdrawEvent() const;
        TSharedPtr<FRefundEvent> GetRefundEvent() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEvent, ESPMode::ThreadSafe> FEventPtr;
}