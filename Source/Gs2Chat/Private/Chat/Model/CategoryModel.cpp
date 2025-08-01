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

#include "Chat/Model/CategoryModel.h"

namespace Gs2::Chat::Model
{
    FCategoryModel::FCategoryModel():
        CategoryModelIdValue(TOptional<FString>()),
        CategoryValue(TOptional<int32>()),
        RejectAccessTokenPostValue(TOptional<FString>())
    {
    }

    FCategoryModel::FCategoryModel(
        const FCategoryModel& From
    ):
        CategoryModelIdValue(From.CategoryModelIdValue),
        CategoryValue(From.CategoryValue),
        RejectAccessTokenPostValue(From.RejectAccessTokenPostValue)
    {
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithCategoryModelId(
        const TOptional<FString> CategoryModelId
    )
    {
        this->CategoryModelIdValue = CategoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithCategory(
        const TOptional<int32> Category
    )
    {
        this->CategoryValue = Category;
        return SharedThis(this);
    }

    TSharedPtr<FCategoryModel> FCategoryModel::WithRejectAccessTokenPost(
        const TOptional<FString> RejectAccessTokenPost
    )
    {
        this->RejectAccessTokenPostValue = RejectAccessTokenPost;
        return SharedThis(this);
    }
    TOptional<FString> FCategoryModel::GetCategoryModelId() const
    {
        return CategoryModelIdValue;
    }
    TOptional<int32> FCategoryModel::GetCategory() const
    {
        return CategoryValue;
    }

    FString FCategoryModel::GetCategoryString() const
    {
        if (!CategoryValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CategoryValue.GetValue());
    }
    TOptional<FString> FCategoryModel::GetRejectAccessTokenPost() const
    {
        return RejectAccessTokenPostValue;
    }

    TOptional<FString> FCategoryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):model:(?<category>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):model:(?<category>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):model:(?<category>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FCategoryModel::GetCategoryFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+):model:(?<category>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FCategoryModel> FCategoryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCategoryModel>()
            ->WithCategoryModelId(Data->HasField(ANSI_TO_TCHAR("categoryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("categoryModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCategory(Data->HasField(ANSI_TO_TCHAR("category")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("category"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRejectAccessTokenPost(Data->HasField(ANSI_TO_TCHAR("rejectAccessTokenPost")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rejectAccessTokenPost"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCategoryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CategoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryModelId", CategoryModelIdValue.GetValue());
        }
        if (CategoryValue.IsSet())
        {
            JsonRootObject->SetNumberField("category", CategoryValue.GetValue());
        }
        if (RejectAccessTokenPostValue.IsSet())
        {
            JsonRootObject->SetStringField("rejectAccessTokenPost", RejectAccessTokenPostValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FCategoryModel::TypeName = "CategoryModel";
}