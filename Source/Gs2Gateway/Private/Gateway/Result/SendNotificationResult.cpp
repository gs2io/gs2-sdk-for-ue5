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

#include "Gateway/Result/SendNotificationResult.h"

namespace Gs2::Gateway::Result
{
    FSendNotificationResult::FSendNotificationResult():
        ProtocolValue(TOptional<FString>())
    {
    }

    FSendNotificationResult::FSendNotificationResult(
        const FSendNotificationResult& From
    ):
        ProtocolValue(From.ProtocolValue)
    {
    }

    TSharedPtr<FSendNotificationResult> FSendNotificationResult::WithProtocol(
        const TOptional<FString> Protocol
    )
    {
        this->ProtocolValue = Protocol;
        return SharedThis(this);
    }

    TOptional<FString> FSendNotificationResult::GetProtocol() const
    {
        return ProtocolValue;
    }

    TSharedPtr<FSendNotificationResult> FSendNotificationResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendNotificationResult>()
            ->WithProtocol(Data->HasField("protocol") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("protocol", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSendNotificationResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProtocolValue.IsSet())
        {
            JsonRootObject->SetStringField("protocol", ProtocolValue.GetValue());
        }
        return JsonRootObject;
    }
}