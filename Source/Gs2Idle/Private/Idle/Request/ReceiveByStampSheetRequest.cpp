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

#include "Idle/Request/ReceiveByStampSheetRequest.h"

namespace Gs2::Idle::Request
{
    FReceiveByStampSheetRequest::FReceiveByStampSheetRequest():
        StampSheetValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FReceiveByStampSheetRequest::FReceiveByStampSheetRequest(
        const FReceiveByStampSheetRequest& From
    ):
        StampSheetValue(From.StampSheetValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FReceiveByStampSheetRequest> FReceiveByStampSheetRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveByStampSheetRequest> FReceiveByStampSheetRequest::WithStampSheet(
        const TOptional<FString> StampSheet
    )
    {
        this->StampSheetValue = StampSheet;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveByStampSheetRequest> FReceiveByStampSheetRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FReceiveByStampSheetRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FReceiveByStampSheetRequest::GetStampSheet() const
    {
        return StampSheetValue;
    }

    TOptional<FString> FReceiveByStampSheetRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FReceiveByStampSheetRequest> FReceiveByStampSheetRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveByStampSheetRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStampSheet(Data->HasField(ANSI_TO_TCHAR("stampSheet")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stampSheet"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField(ANSI_TO_TCHAR("keyId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("keyId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FReceiveByStampSheetRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StampSheetValue.IsSet())
        {
            JsonRootObject->SetStringField("stampSheet", StampSheetValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}