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

#include "Lottery/Model/DrawnPrize.h"

namespace Gs2::Lottery::Model
{
    FDrawnPrize::FDrawnPrize():
        PrizeIdValue(TOptional<FString>()),
        AcquireActionsValue(nullptr)
    {
    }

    FDrawnPrize::FDrawnPrize(
        const FDrawnPrize& From
    ):
        PrizeIdValue(From.PrizeIdValue),
        AcquireActionsValue(From.AcquireActionsValue)
    {
    }

    TSharedPtr<FDrawnPrize> FDrawnPrize::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FDrawnPrize> FDrawnPrize::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FDrawnPrize::GetPrizeId() const
    {
        return PrizeIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FDrawnPrize::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    TSharedPtr<FDrawnPrize> FDrawnPrize::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDrawnPrize>()
            ->WithPrizeId(Data->HasField("prizeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireActions(Data->HasField("acquireActions") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("acquireActions") && Data->HasTypedField<EJson::Array>("acquireActions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("acquireActions"))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDrawnPrize::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeId", PrizeIdValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        return JsonRootObject;
    }

    FString FDrawnPrize::TypeName = "DrawnPrize";
}