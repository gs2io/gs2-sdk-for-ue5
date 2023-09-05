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

#include "JobQueue/Request/DeleteByStampTaskRequest.h"

namespace Gs2::JobQueue::Request
{
    FDeleteByStampTaskRequest::FDeleteByStampTaskRequest():
        StampTaskValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FDeleteByStampTaskRequest::FDeleteByStampTaskRequest(
        const FDeleteByStampTaskRequest& From
    ):
        StampTaskValue(From.StampTaskValue),
        KeyIdValue(From.KeyIdValue)
    {
    }

    TSharedPtr<FDeleteByStampTaskRequest> FDeleteByStampTaskRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteByStampTaskRequest> FDeleteByStampTaskRequest::WithStampTask(
        const TOptional<FString> StampTask
    )
    {
        this->StampTaskValue = StampTask;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteByStampTaskRequest> FDeleteByStampTaskRequest::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteByStampTaskRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteByStampTaskRequest::GetStampTask() const
    {
        return StampTaskValue;
    }

    TOptional<FString> FDeleteByStampTaskRequest::GetKeyId() const
    {
        return KeyIdValue;
    }

    TSharedPtr<FDeleteByStampTaskRequest> FDeleteByStampTaskRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteByStampTaskRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithStampTask(Data->HasField("stampTask") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("stampTask", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("keyId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteByStampTaskRequest::ToJson() const
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