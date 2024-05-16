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

#include "Guild/Result/SendRequestResult.h"

namespace Gs2::Guild::Result
{
    FSendRequestResult::FSendRequestResult():
        ItemValue(nullptr),
        SendMemberRequestValue(nullptr)
    {
    }

    FSendRequestResult::FSendRequestResult(
        const FSendRequestResult& From
    ):
        ItemValue(From.ItemValue),
        SendMemberRequestValue(From.SendMemberRequestValue)
    {
    }

    TSharedPtr<FSendRequestResult> FSendRequestResult::WithItem(
        const TSharedPtr<Model::FGuild> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSendRequestResult> FSendRequestResult::WithSendMemberRequest(
        const TSharedPtr<Model::FSendMemberRequest> SendMemberRequest
    )
    {
        this->SendMemberRequestValue = SendMemberRequest;
        return SharedThis(this);
    }

    TSharedPtr<Model::FGuild> FSendRequestResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FSendMemberRequest> FSendRequestResult::GetSendMemberRequest() const
    {
        if (!SendMemberRequestValue.IsValid())
        {
            return nullptr;
        }
        return SendMemberRequestValue;
    }

    TSharedPtr<FSendRequestResult> FSendRequestResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSendRequestResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithSendMemberRequest(Data->HasField(ANSI_TO_TCHAR("sendMemberRequest")) ? [Data]() -> Model::FSendMemberRequestPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("sendMemberRequest")))
                    {
                        return nullptr;
                    }
                    return Model::FSendMemberRequest::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("sendMemberRequest")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSendRequestResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (SendMemberRequestValue != nullptr && SendMemberRequestValue.IsValid())
        {
            JsonRootObject->SetObjectField("sendMemberRequest", SendMemberRequestValue->ToJson());
        }
        return JsonRootObject;
    }
}