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

#include "SeasonRating/Result/GetBallotResult.h"

namespace Gs2::SeasonRating::Result
{
    FGetBallotResult::FGetBallotResult():
        ItemValue(nullptr),
        BodyValue(TOptional<FString>()),
        SignatureValue(TOptional<FString>())
    {
    }

    FGetBallotResult::FGetBallotResult(
        const FGetBallotResult& From
    ):
        ItemValue(From.ItemValue),
        BodyValue(From.BodyValue),
        SignatureValue(From.SignatureValue)
    {
    }

    TSharedPtr<FGetBallotResult> FGetBallotResult::WithItem(
        const TSharedPtr<Model::FBallot> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotResult> FGetBallotResult::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FGetBallotResult> FGetBallotResult::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }

    TSharedPtr<Model::FBallot> FGetBallotResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FGetBallotResult::GetBody() const
    {
        return BodyValue;
    }

    TOptional<FString> FGetBallotResult::GetSignature() const
    {
        return SignatureValue;
    }

    TSharedPtr<FGetBallotResult> FGetBallotResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetBallotResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FBallotPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FBallot::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithBody(Data->HasField("body") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("body", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSignature(Data->HasField("signature") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("signature", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetBallotResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (BodyValue.IsSet())
        {
            JsonRootObject->SetStringField("body", BodyValue.GetValue());
        }
        if (SignatureValue.IsSet())
        {
            JsonRootObject->SetStringField("signature", SignatureValue.GetValue());
        }
        return JsonRootObject;
    }
}