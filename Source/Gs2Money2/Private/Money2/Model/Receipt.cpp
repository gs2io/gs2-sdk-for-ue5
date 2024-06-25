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

#include "Money2/Model/Receipt.h"

namespace Gs2::Money2::Model
{
    FReceipt::FReceipt():
        StoreValue(TOptional<FString>()),
        TransactionIDValue(TOptional<FString>()),
        PayloadValue(TOptional<FString>())
    {
    }

    FReceipt::FReceipt(
        const FReceipt& From
    ):
        StoreValue(From.StoreValue),
        TransactionIDValue(From.TransactionIDValue),
        PayloadValue(From.PayloadValue)
    {
    }

    TSharedPtr<FReceipt> FReceipt::WithStore(
        const TOptional<FString> Store
    )
    {
        this->StoreValue = Store;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithTransactionID(
        const TOptional<FString> TransactionID
    )
    {
        this->TransactionIDValue = TransactionID;
        return SharedThis(this);
    }

    TSharedPtr<FReceipt> FReceipt::WithPayload(
        const TOptional<FString> Payload
    )
    {
        this->PayloadValue = Payload;
        return SharedThis(this);
    }
    TOptional<FString> FReceipt::GetStore() const
    {
        return StoreValue;
    }
    TOptional<FString> FReceipt::GetTransactionID() const
    {
        return TransactionIDValue;
    }
    TOptional<FString> FReceipt::GetPayload() const
    {
        return PayloadValue;
    }

    TSharedPtr<FReceipt> FReceipt::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceipt>()
            ->WithStore(Data->HasField(ANSI_TO_TCHAR("store")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("store"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionID(Data->HasField(ANSI_TO_TCHAR("transactionID")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionID"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FReceipt::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StoreValue.IsSet())
        {
            JsonRootObject->SetStringField("store", StoreValue.GetValue());
        }
        if (TransactionIDValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionID", TransactionIDValue.GetValue());
        }
        if (PayloadValue.IsSet())
        {
            JsonRootObject->SetStringField("payload", PayloadValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FReceipt::TypeName = "Receipt";
}