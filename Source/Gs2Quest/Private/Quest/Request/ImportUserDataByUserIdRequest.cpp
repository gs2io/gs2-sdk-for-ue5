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

#include "Quest/Request/ImportUserDataByUserIdRequest.h"

namespace Gs2::Quest::Request
{
    FImportUserDataByUserIdRequest::FImportUserDataByUserIdRequest():
        UserIdValue(TOptional<FString>()),
        UploadTokenValue(TOptional<FString>())
    {
    }

    FImportUserDataByUserIdRequest::FImportUserDataByUserIdRequest(
        const FImportUserDataByUserIdRequest& From
    ):
        UserIdValue(From.UserIdValue),
        UploadTokenValue(From.UploadTokenValue)
    {
    }

    TSharedPtr<FImportUserDataByUserIdRequest> FImportUserDataByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FImportUserDataByUserIdRequest> FImportUserDataByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FImportUserDataByUserIdRequest> FImportUserDataByUserIdRequest::WithUploadToken(
        const TOptional<FString> UploadToken
    )
    {
        this->UploadTokenValue = UploadToken;
        return SharedThis(this);
    }

    TSharedPtr<FImportUserDataByUserIdRequest> FImportUserDataByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FImportUserDataByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FImportUserDataByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FImportUserDataByUserIdRequest::GetUploadToken() const
    {
        return UploadTokenValue;
    }

    TOptional<FString> FImportUserDataByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FImportUserDataByUserIdRequest> FImportUserDataByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FImportUserDataByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUploadToken(Data->HasField("uploadToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("uploadToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FImportUserDataByUserIdRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (UploadTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("uploadToken", UploadTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}