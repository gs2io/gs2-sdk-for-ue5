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

// ReSharper disable CppUnusedIncludeDirective

#include "Datastore/Domain/Iterator/DescribeDataObjectsIterator.h"
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Domain/Model/User.h"

namespace Gs2::Datastore::Domain::Iterator
{

    FDescribeDataObjectsIterator::FDescribeDataObjectsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> Status
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Status(Status)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeDataObjectsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObject>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeDataObjectsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeDataObjectsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeDataObjectsIterator::FIterator& FDescribeDataObjectsIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId(),
            "DataObject"
        );
            if (Self->Cache->IsListCached(
                Gs2::Datastore::Model::FDataObject::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Datastore::Model::FDataObjectPtr>>();
                *Range = Self->Cache->List<Gs2::Datastore::Model::FDataObject>(
                    ListParentKey
                );
                Range->RemoveAll([this](const Gs2::Datastore::Model::FDataObjectPtr& Item) { return Self->Status && Item->GetStatus() == Self->Status; });
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeDataObjects(
                MakeShared<Gs2::Datastore::Request::FDescribeDataObjectsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithStatus(Self->Status)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ListParentKey,
                    Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeDataObjectsIterator::FIterator FDescribeDataObjectsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeDataObjectsIterator::FIterator FDescribeDataObjectsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeDataObjectsIterator::FIterator FDescribeDataObjectsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

