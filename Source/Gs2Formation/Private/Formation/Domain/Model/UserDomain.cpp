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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Formation::Domain::Iterator::FDescribeMoldsByUserIdIteratorPtr FUserDomain::Molds(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeMoldsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeMolds(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Mold"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeMolds(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FMold::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Mold"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain> FUserDomain::Mold(
        const FString MoldModelName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FMoldDomain>(
            Gs2,
            NamespaceName,
            UserId,
            MoldModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MoldModelName)
        );
    }

    Gs2::Formation::Domain::Iterator::FDescribePropertyFormsByUserIdIteratorPtr FUserDomain::PropertyForms(
        const FString PropertyFormModelName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribePropertyFormsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            PropertyFormModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribePropertyForms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FPropertyForm::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "PropertyForm"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribePropertyForms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FPropertyForm::TypeName,
            Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "PropertyForm"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FPropertyFormDomain> FUserDomain::PropertyForm(
        const FString PropertyFormModelName,
        const FString PropertyId
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FPropertyFormDomain>(
            Gs2,
            NamespaceName,
            UserId,
            PropertyFormModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyFormModelName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

