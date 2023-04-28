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

#include "News/Model/View.h"

namespace Gs2::News::Model
{
    FView::FView():
        ContentsValue(nullptr),
        RemoveContentsValue(nullptr)
    {
    }

    FView::FView(
        const FView& From
    ):
        ContentsValue(From.ContentsValue),
        RemoveContentsValue(From.RemoveContentsValue)
    {
    }

    TSharedPtr<FView> FView::WithContents(
        const TSharedPtr<TArray<TSharedPtr<Model::FContent>>> Contents
    )
    {
        this->ContentsValue = Contents;
        return SharedThis(this);
    }

    TSharedPtr<FView> FView::WithRemoveContents(
        const TSharedPtr<TArray<TSharedPtr<Model::FContent>>> RemoveContents
    )
    {
        this->RemoveContentsValue = RemoveContents;
        return SharedThis(this);
    }
    TSharedPtr<TArray<TSharedPtr<Model::FContent>>> FView::GetContents() const
    {
        return ContentsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FContent>>> FView::GetRemoveContents() const
    {
        return RemoveContentsValue;
    }

    TSharedPtr<FView> FView::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FView>()
            ->WithContents(Data->HasField("contents") ? [Data]() -> TSharedPtr<TArray<Model::FContentPtr>>
                {
                    auto v = MakeShared<TArray<Model::FContentPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("contents") && Data->HasTypedField<EJson::Array>("contents"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("contents"))
                        {
                            v->Add(Model::FContent::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FContentPtr>>())
            ->WithRemoveContents(Data->HasField("removeContents") ? [Data]() -> TSharedPtr<TArray<Model::FContentPtr>>
                {
                    auto v = MakeShared<TArray<Model::FContentPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("removeContents") && Data->HasTypedField<EJson::Array>("removeContents"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("removeContents"))
                        {
                            v->Add(Model::FContent::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FContentPtr>>());
    }

    TSharedPtr<FJsonObject> FView::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContentsValue != nullptr && ContentsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ContentsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("contents", v);
        }
        if (RemoveContentsValue != nullptr && RemoveContentsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RemoveContentsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("removeContents", v);
        }
        return JsonRootObject;
    }

    FString FView::TypeName = "View";
}