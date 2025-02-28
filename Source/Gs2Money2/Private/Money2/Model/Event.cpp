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

#include "Money2/Model/Event.h"

namespace Gs2::Money2::Model
{
    FEvent::FEvent():
        EventIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        EventTypeValue(TOptional<FString>()),
        VerifyReceiptEventValue(nullptr),
        DepositEventValue(nullptr),
        WithdrawEventValue(nullptr),
        RefundEventValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FEvent::FEvent(
        const FEvent& From
    ):
        EventIdValue(From.EventIdValue),
        TransactionIdValue(From.TransactionIdValue),
        UserIdValue(From.UserIdValue),
        EventTypeValue(From.EventTypeValue),
        VerifyReceiptEventValue(From.VerifyReceiptEventValue),
        DepositEventValue(From.DepositEventValue),
        WithdrawEventValue(From.WithdrawEventValue),
        RefundEventValue(From.RefundEventValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FEvent> FEvent::WithEventId(
        const TOptional<FString> EventId
    )
    {
        this->EventIdValue = EventId;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithEventType(
        const TOptional<FString> EventType
    )
    {
        this->EventTypeValue = EventType;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithVerifyReceiptEvent(
        const TSharedPtr<FVerifyReceiptEvent> VerifyReceiptEvent
    )
    {
        this->VerifyReceiptEventValue = VerifyReceiptEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithDepositEvent(
        const TSharedPtr<FDepositEvent> DepositEvent
    )
    {
        this->DepositEventValue = DepositEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithWithdrawEvent(
        const TSharedPtr<FWithdrawEvent> WithdrawEvent
    )
    {
        this->WithdrawEventValue = WithdrawEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithRefundEvent(
        const TSharedPtr<FRefundEvent> RefundEvent
    )
    {
        this->RefundEventValue = RefundEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEvent> FEvent::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FEvent::GetEventId() const
    {
        return EventIdValue;
    }
    TOptional<FString> FEvent::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FEvent::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEvent::GetEventType() const
    {
        return EventTypeValue;
    }
    TSharedPtr<FVerifyReceiptEvent> FEvent::GetVerifyReceiptEvent() const
    {
        return VerifyReceiptEventValue;
    }
    TSharedPtr<FDepositEvent> FEvent::GetDepositEvent() const
    {
        return DepositEventValue;
    }
    TSharedPtr<FWithdrawEvent> FEvent::GetWithdrawEvent() const
    {
        return WithdrawEventValue;
    }
    TSharedPtr<FRefundEvent> FEvent::GetRefundEvent() const
    {
        return RefundEventValue;
    }
    TOptional<int64> FEvent::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEvent::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEvent::GetRevision() const
    {
        return RevisionValue;
    }

    FString FEvent::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FEvent::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):event:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):event:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):event:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEvent::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):event:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FEvent> FEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEvent>()
            ->WithEventId(Data->HasField(ANSI_TO_TCHAR("eventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEventType(Data->HasField(ANSI_TO_TCHAR("eventType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVerifyReceiptEvent(Data->HasField(ANSI_TO_TCHAR("verifyReceiptEvent")) ? [Data]() -> Model::FVerifyReceiptEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyReceiptEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FVerifyReceiptEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("verifyReceiptEvent")));
                 }() : nullptr)
            ->WithDepositEvent(Data->HasField(ANSI_TO_TCHAR("depositEvent")) ? [Data]() -> Model::FDepositEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("depositEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FDepositEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("depositEvent")));
                 }() : nullptr)
            ->WithWithdrawEvent(Data->HasField(ANSI_TO_TCHAR("withdrawEvent")) ? [Data]() -> Model::FWithdrawEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FWithdrawEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("withdrawEvent")));
                 }() : nullptr)
            ->WithRefundEvent(Data->HasField(ANSI_TO_TCHAR("refundEvent")) ? [Data]() -> Model::FRefundEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("refundEvent")))
                    {
                        return nullptr;
                    }
                    return Model::FRefundEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("refundEvent")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("eventId", EventIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (EventTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("eventType", EventTypeValue.GetValue());
        }
        if (VerifyReceiptEventValue != nullptr && VerifyReceiptEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("verifyReceiptEvent", VerifyReceiptEventValue->ToJson());
        }
        if (DepositEventValue != nullptr && DepositEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("depositEvent", DepositEventValue->ToJson());
        }
        if (WithdrawEventValue != nullptr && WithdrawEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("withdrawEvent", WithdrawEventValue->ToJson());
        }
        if (RefundEventValue != nullptr && RefundEventValue.IsValid())
        {
            JsonRootObject->SetObjectField("refundEvent", RefundEventValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FEvent::TypeName = "Event";
}