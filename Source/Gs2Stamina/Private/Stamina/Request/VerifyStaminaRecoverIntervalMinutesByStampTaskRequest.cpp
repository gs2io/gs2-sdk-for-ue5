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

#include "Stamina/Request/VerifyStaminaRecoverIntervalMinutesByStampTaskRequest.h"

namespace Gs2::Stamina::Request
{
    FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest():
        StampTaskValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest(
        const FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest& From
    ):
        StampTaskValue(From.StampTaskValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::WithStampTask(
        const TOptional<FString> StampTask
    )
    {
        this->StampTaskValue = StampTask;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::GetStampTask() const
    {
        return StampTaskValue;
    }

    TOptional<FString> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithStampTask(Data->HasField(ANSI_TO_TCHAR("stampTask")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stampTask"), v))
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

    TSharedPtr<FJsonObject> FVerifyStaminaRecoverIntervalMinutesByStampTaskRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (StampTaskValue.IsSet())
        {
            JsonRootObject->SetStringField("stampTask", StampTaskValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }
}