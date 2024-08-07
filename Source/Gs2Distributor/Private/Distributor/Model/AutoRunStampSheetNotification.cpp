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

#include "Distributor/Model/AutoRunStampSheetNotification.h"

namespace Gs2::Distributor::Model
{

    TSharedPtr<FAutoRunStampSheetNotification> FAutoRunStampSheetNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FAutoRunStampSheetNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FAutoRunStampSheetNotification> FAutoRunStampSheetNotification::WithUserId(
        const TOptional<FString> UserId
    ) {
        UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FAutoRunStampSheetNotification::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FAutoRunStampSheetNotification> FAutoRunStampSheetNotification::WithTransactionId(
        const TOptional<FString> TransactionId
    ) {
        TransactionIdValue = TransactionId;
        return SharedThis(this);
    }
    TOptional<FString> FAutoRunStampSheetNotification::GetTransactionId() const
    {
        return TransactionIdValue;
    }

    TSharedPtr<FAutoRunStampSheetNotification> FAutoRunStampSheetNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAutoRunStampSheetNotification>()
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
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
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
