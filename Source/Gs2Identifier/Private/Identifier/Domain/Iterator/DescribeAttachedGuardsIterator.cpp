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

#include "Identifier/Domain/Iterator/DescribeAttachedGuardsIterator.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Identifier::Domain::Iterator
{

    FDescribeAttachedGuardsIterator::FDescribeAttachedGuardsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client,
        const TOptional<FString> UserName,
        const TOptional<FString> ClientId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        ClientId(ClientId),
        UserName(UserName)
    {
    }

    FDescribeAttachedGuardsIterator::FDescribeAttachedGuardsIterator(
        const FDescribeAttachedGuardsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ClientId(From.ClientId),
        UserName(From.UserName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeAttachedGuardsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Identifier::Model::FIdentifierEntry>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeAttachedGuardsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeAttachedGuardsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeAttachedGuardsIterator::FIterator& FDescribeAttachedGuardsIterator::FIterator::operator++()
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
            const auto ListParentKey = FStringDomain::CreateCacheParentKey(
                "NamespaceGrn"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Identifier::Model::FIdentifierEntry>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Identifier::Model::FIdentifierEntryPtr& Item) { return Self->ClientId && Item->GetClientId() != Self->ClientId; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeAttachedGuards(
                MakeShared<Gs2::Identifier::Request::FDescribeAttachedGuardsRequest>()
                    ->WithClientId(Self->ClientId)
                    ->WithUserName(Self->UserName)
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
            if (!Range.IsValid())
            {
                Range = MakeShared<TArray<Identifier::Model::FIdentifierEntryPtr>>();
            }
            for (auto Item : *R->GetItems())
            {
                Range->Add(MakeShared<Identifier::Model::FIdentifierEntry>(Item));
            }
            for (auto Item : *R->GetItems())
            {
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FIdentifierEntry::TypeName,
                    ListParentKey,
                    Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    ),
                    MakeShared<Identifier::Model::FIdentifierEntry>(Item),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Identifier::Model::FIdentifierEntryPtr& Item) { return Self->ClientId && Item->GetClientId() != Self->ClientId; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Identifier::Model::FIdentifierEntry::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeAttachedGuardsIterator::FIterator FDescribeAttachedGuardsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeAttachedGuardsIterator::FIterator FDescribeAttachedGuardsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeAttachedGuardsIterator::FIterator FDescribeAttachedGuardsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

