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

#include "Guild/Model/ReceiveMemberRequest.h"

namespace Gs2::Guild::Model
{
    FReceiveMemberRequest::FReceiveMemberRequest():
        UserIdValue(TOptional<FString>()),
        TargetGuildNameValue(TOptional<FString>())
    {
    }

    FReceiveMemberRequest::FReceiveMemberRequest(
        const FReceiveMemberRequest& From
    ):
        UserIdValue(From.UserIdValue),
        TargetGuildNameValue(From.TargetGuildNameValue)
    {
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithTargetGuildName(
        const TOptional<FString> TargetGuildName
    )
    {
        this->TargetGuildNameValue = TargetGuildName;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveMemberRequest::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FReceiveMemberRequest::GetTargetGuildName() const
    {
        return TargetGuildNameValue;
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveMemberRequest>()
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetGuildName(Data->HasField("targetGuildName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("targetGuildName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FReceiveMemberRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TargetGuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField("targetGuildName", TargetGuildNameValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FReceiveMemberRequest::TypeName = "ReceiveMemberRequest";
}